/**
 * Retrieves the width of the map.
 * @returns {Promise<void>} A promise that resolves when the width is retrieved.
 */
const getMapWidth = async () => {
  const res = await fetch("http://localhost:2707/mapWidth");
  return res.json();
};

/**
 * Fetches the bit at the specified index from the server.
 * @param {number} i - The index of the bit to fetch.
 * @returns {Promise} - A promise that resolves with the fetched bit.
 */
const getMapPiece = async (i) => {
  const res = await fetch(`http://localhost:2707/piece/${i}`);
  return res.json();
};

/**
 * Creates a grid element with the specified map width.
 * @param {number} mapWidth - The width of the map.
 */

function createGrid(mapWidth) {
  const div = document.createElement("div");
  div.id = "asyncGrid";
  div.style.display = "grid";
  div.style.gridTemplateColumns = `repeat(${mapWidth}, 1fr)`;
  div.style.gridTemplateRows = `repeat(${mapWidth}, 1fr)`;
  div.style.width = "fit-content";
  div.style.height = "fit-content";
  document.body.appendChild(div);
}

/**
 * Displays an SVG element asynchronously at the specified coordinates.
 *
 * @param {string} svg - The SVG element to be displayed.
 * @param {number} x - The x-coordinate of the grid cell where the SVG element will be displayed.
 * @param {number} y - The y-coordinate of the grid cell where the SVG element will be displayed.
 */
async function displayPiece(svg, x, y) {
  const svgElement = document.createElement("div");
  svgElement.innerHTML = svg;

  const width = svgElement.lastChild.getAttribute("width");
  const height = svgElement.lastChild.getAttribute("height");

  svgElement.style.width = `${width}px`;
  svgElement.style.height = `${height}px`;
  svgElement.style.gridColumn = x + 1;
  svgElement.style.gridRow = y + 1;
  svgElement.style.padding = 0;
  svgElement.style.margin = 0;
  document.getElementById("asyncGrid").appendChild(svgElement);
}

async function displayMap() {
  // FIXME !
    const startTime = Date.now();

    const width = await getMapWidth();

    createGrid(width);
    let promises = [];
    for (let i = 0; i < width * width; i++) {
      //let piece = await getMapPiece(i);
      //displayPiece(piece.svg, piece.x, piece.y);
      let promise = getMapPiece(i).then((value) => displayPiece(value.svg, value.x, value.y));
      promises.push(promise);
    }

   await Promise.all(promises);

    const endTime = Date.now();
    return endTime - startTime;
  // don't forget you can use above functions to help you and also make your own
}

// Your code here, the html page will load your script and launch it
// Catch errors if you push your testing code so the Moulinette doesn't fail

// You will also have to export the displayMap function for the tests

module.exports = {
  displayMap,
};
