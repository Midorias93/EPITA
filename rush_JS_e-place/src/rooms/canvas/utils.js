// This file handles the room canvas DOM manipulation
// Functions includes:
// - initCanvas (initialize the canvas)
// - renderCanvasUpdate (render a canvas update)
// - getPlacementData (get the necessary data to place a pixel)
// - toggleTooltip (toggle the tooltip and display the pixel's information)

import $ from "jquery";

const canvasContainer = $("#canvas-container")?.[0];
const canvas = $("#canvas")?.[0];
const canvasCtx = canvas.getContext("2d");
const selector = $("#selector")?.[0];

const positionTooltip = $("#position-tooltip")?.[0];
const tooltip = $("#tooltip")?.[0];
const colorPicker = $("#color-picker")?.[0];
const colorWheelContainer = $("#color-wheel-container")?.[0];
const colorWheel = $("#color-wheel")?.[0];

/**
 * Global variables
 */
let board, palette, selectedColorIdx;
let animation;

const zoomSpeed = 1 / 25;
let zoom = 2.5;

let x, y;
let cx = 0;
let cy = 0;
let target = { x: 0, y: 0 };
let isDrag = false;

/**
 * Returns the necessary data to place a pixel
 * @returns {{color: number, posX: number, posX: number}} the data
 */
export const getPlacementData = () => ({
  color: selectedColorIdx,
  posX: target.x,
  posY: target.y,
});

/**
 * Toggle the tooltip and display the pixel's information
 * @param {boolean} state
 */
export const toggleTooltip = async (state = false) => {
  tooltip.style.display = state ? "flex" : "none";

  if (state) {
    // FIXME: You should implement or call a function to get the pixel's information
    // and display it. Make use of target.x and target.y to get the pixel's position.
  }
};

/**
 * Calculate the target position according to the top left corner of the canvas
 * @param {*} event
 * @returns {x: number, y: number} the target position
 */
const calculateTarget = (event) => {
  const rect = canvas.getBoundingClientRect();
  const scaleX = canvas.width / rect.width;
  const scaleY = canvas.height / rect.height;
  const canvasLeft = rect.left + window.pageXOffset;
  const canvasTop = rect.top + window.pageYOffset;

  return {
    x: Math.floor(
      ((event?.pageX ?? window.innerWidth / 2) - canvasLeft) * scaleX
    ),
    y: Math.floor(
      ((event?.pageY ?? window.innerHeight / 2) - canvasTop) * scaleY
    ),
  };
};

/**
 * Update the position tooltip
 * @param {*} event
 */
const positionUpdate = (event) => positionDisplay(calculateTarget(event));

/**
 * Update the position tooltip
 * @param {{x: number, y: number}} target
 */
const positionDisplay = ({ x, y }) => {
  positionTooltip.innerText = `X=${x} Y=${y}`;
  canvas.style.transform = `translate(${cx}px, ${cy}px) scale(${zoom})`;

  // We add the canvas.width * zoom to make cx and cy positive
  let selectorX = cx + canvas.width * zoom;
  let selectorY = cy + canvas.height * zoom;

  // Make odd canvas align
  if (canvas.width % 2 !== 0) {
    selectorX += zoom / 2;
    selectorY += zoom / 2;
  }

  // Find the translate
  selectorX %= zoom;
  selectorY %= zoom;

  // Center selector on the pixel
  selectorX -= zoom / 2;
  selectorY -= zoom / 2;

  selector.style.transform = `translate(${selectorX}px, ${selectorY}px) scale(${zoom})`;
};

// Toggle the color wheel on click on the color picker
colorPicker.addEventListener("click", () => {
  const state = colorWheelContainer.style.display;
  colorWheelContainer.style.display =
    !state || state === "none" ? "block" : "none";
});

/**
 * Transform #RRGGBB to 0xBBGGRRAA
 * @param {string} hex
 * @returns {number} the 32 bits color
 */
const transformHexTo32Bits = (hex) => {
  const reverse = hex.substring(1).match(/.{2}/g).reverse().join("");
  return parseInt(`0xFF${reverse}`, 16);
};

/**
 * Render the canvas
 * @param {number[]} pixels
 * @param {string[]} colors
 */
const renderCanvas = (pixels, colors) => {
  const img = new ImageData(canvas.width, canvas.height);
  const data = new Uint32Array(img.data.buffer);

  board = pixels;
  palette = colors;
  for (let i = 0; i < pixels.length; i++) {
    data[i] = transformHexTo32Bits(colors[pixels[i]]);
  }

  canvasCtx.putImageData(img, 0, 0);
  canvasCtx.imageSmoothingEnabled = false;
  canvas.style.imageRendering = "pixelated";

  // Remove all the colors from the color wheel
  while (colorWheel.firstChild) {
    colorWheel.removeChild(colorWheel.firstChild);
  }

  // Add the colors to the color wheel
  for (let i = 0; i < colors.length; i++) {
    const btn = document.createElement("button");
    colorWheel.appendChild(btn);

    btn.addEventListener("click", () => {
      selectedColorIdx = i;
      colorPicker.style.color = colors[i];
      colorPicker.style.border = `${colors[i]} 0.1rem solid`;
    });

    btn.style.backgroundColor = colors[i];
  }
};

/**
 * Initialize the canvas
 * @param {*} roomConfig
 * @param {number[]} pixels
 */
export const initCanvas = (roomConfig, pixels) => {
  const canvasDimensions = roomConfig.metadata.canvasDimensions;
  canvas.width = canvasDimensions;
  canvas.height = canvasDimensions;

  positionDisplay({ x: canvasDimensions / 2, y: canvasDimensions / 2 });
  selectedColorIdx = 0;

  const roomColors = roomConfig.settings.roomColors.split(",");
  colorPicker.style.color = roomColors[0];
  colorPicker.style.border = `${roomColors[0]} 0.1rem solid`;

  renderCanvas(pixels, roomColors);
};

/**
 * Update the canvas
 * @param {string} color
 * @param {number} x
 * @param {number} y
 */
export const renderCanvasUpdate = (color, x, y) => {
  const img = new ImageData(canvas.width, canvas.height);
  const data = new Uint32Array(img.data.buffer);

  board[y * canvas.width + x] = color;
  for (let i = 0; i < board.length; i++) {
    data[i] = transformHexTo32Bits(palette[board[i]]);
  }

  canvasCtx.putImageData(img, 0, 0);
};

/**
 * Reset the canvas values
 */
export const resetValues = () => {
  zoom = 2.5;
  x = 0;
  y = 0;
  cx = 0;
  cy = 0;
  isDrag = false;

  positionDisplay({ x, y });
  colorWheelContainer.style.display = "none";
  toggleTooltip(false);
};

// Handle scroll on canvas
document.addEventListener("wheel", (e) => {
  // Make sure we're scrolling on the canvas or the body and not the UI
  if (e.target !== canvas && e.target !== canvasContainer) return;

  clearInterval(animation);
  toggleTooltip(false);

  const delta = Math.sign(e.deltaY) * zoomSpeed;
  const zoomFactor = 1 + delta;
  const oldZoom = zoom;
  const newZoom = Math.max(2.5, Math.min(40, oldZoom * zoomFactor));

  // Get the position of the mouse relative to the canvas
  const mouseX = e.clientX - window.innerWidth / 2;
  const mouseY = e.clientY - window.innerHeight / 2;

  // Calculate the new center point based on the mouse position
  const newCx = mouseX - (mouseX - cx) * (newZoom / oldZoom);
  const newCy = mouseY - (mouseY - cy) * (newZoom / oldZoom);

  if (newZoom !== oldZoom) {
    zoom = newZoom;
    cx = newCx;
    cy = newCy;
    positionUpdate();
  }
});

// Handle click and drag on canvas
document.addEventListener("mousedown", (e) => {
  // Make sure we're clicking on the canvas or the body and not the UI
  if (e.target !== canvas && e.target !== canvasContainer) return;

  e.preventDefault();

  // Ignore if right click
  if (e.button === 2) return;

  clearInterval(animation);

  isDrag = false;
  x = e.clientX;
  y = e.clientY;

  document.addEventListener("mousemove", mouseMove);
});

// Smooth animation
function easeOutQuart(t, b, c, d) {
  t /= d;
  t--;
  return -c * (t * t * t * t - 1) + b;
}

// Handle when the user releases the mouse
document.addEventListener("mouseup", (e) => {
  document.removeEventListener("mousemove", mouseMove);

  // Make sure we're clicking on the canvas or the body and not the UI
  if (e.target !== canvas && e.target !== canvasContainer) return;

  e.preventDefault();

  // Get the tile position
  target = calculateTarget(e);

  // Make sure we're clicking on the canvas
  if (
    target.x >= 0 &&
    target.x < canvas.width &&
    target.y >= 0 &&
    target.y < canvas.height
  ) {
    // We want to differentiate between a click and a drag
    // If it is a click, we want to move the camera to the clicked tile

    // We wait to see if the position changed
    // If it did not, we consider it a click
    if (!isDrag) {
      const duration = 1000;
      const startZoom = zoom;
      const endZoom = Math.max(15, Math.min(40, zoom));

      // Get the position of the click in relation to the center of the screen
      const clickX = e.clientX - window.innerWidth / 2;
      const clickY = e.clientY - window.innerHeight / 2;
      const canvaswidthzoom = canvas.width * startZoom;
      const canvasheightzoom = canvas.height * startZoom;
      const startx = (cx + canvaswidthzoom / 2) / startZoom;
      const starty = (cy + canvasheightzoom / 2) / startZoom;
      const endx = startx - clickX / startZoom;
      const endy = starty - clickY / startZoom;
      const endCx = endx * endZoom - (canvas.width / 2) * endZoom;
      const endCy = endy * endZoom - (canvas.height / 2) * endZoom;
      const startCx = cx;
      const startCy = cy;
      const startTime = Date.now();

      // If the distance is small enough, we just warp to it
      if (Math.abs(endCx - startCx) < 10 && Math.abs(endCy - startCy) < 10) {
        cx = endCx;
        cy = endCy;
        zoom = endZoom;
        canvas.style.transform = `translate(${cx}px, ${cy}px) scale(${zoom})`;
      } else {
        clearInterval(animation);

        animation = setInterval(() => {
          const elapsed = Date.now() - startTime;
          if (elapsed >= duration) {
            clearInterval(animation);
            return;
          }

          const t = elapsed / duration;
          zoom = easeOutQuart(t, startZoom, endZoom - startZoom, 1);
          cx = easeOutQuart(t, startCx, endCx - startCx, 1);
          cy = easeOutQuart(t, startCy, endCy - startCy, 1);

          positionUpdate();
        }, 10);
      }
    }

    // Toggle the tooltip if it is a click
    toggleTooltip(!isDrag);

    // Update the position of the tooltip
    positionDisplay(target);
  }
});

// Handle mouse move
const mouseMove = (e) => {
  e.preventDefault();

  toggleTooltip(false);
  positionUpdate();

  const dx = e.clientX - x;
  const dy = e.clientY - y;

  // For a big enough delta, we consider it a drag
  if (Math.abs(dx) > 0.5 || Math.abs(dy) > 0.5) {
    isDrag = true;
  }

  x = e.clientX;
  y = e.clientY;
  cx += dx;
  cy += dy;

  canvas.style.transform = `translate(${cx}px, ${cy}px) scale(${zoom})`;
};
