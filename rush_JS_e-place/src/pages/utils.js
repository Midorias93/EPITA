/**
 * Global variables
 */
let [leftTimer, rightTimer] = [null, null];
let [leftSize, rightSize] = [
  localStorage.getItem("leftSize") ?? 0,
  localStorage.getItem("rightSize") ?? 0,
];

const parentContainer = document.getElementById("container");

const leftContainer = document.getElementById("left-container");
const closeLeftButton = document.getElementById("close-left");
const rightContainer = document.getElementById("right-container");
const closeRightButton = document.getElementById("close-right");

leftContainer.classList.toggle("Hidden", !leftSize);

/**
 * Calculate the layout of the home page
 */
export const calculateLayout = () => {
  const parentContainerSize = `${4.5 - leftSize - rightSize}fr`;

  // left and right are reversed because of the grid layout
  parentContainer.style.gridTemplateColumns = `${leftSize}fr ${parentContainerSize} ${rightSize}fr`;
  leftContainer.style.opacity = leftSize;
  rightContainer.style.opacity = rightSize;
};

closeLeftButton.addEventListener("click", () => {
  leftSize = 1 - leftSize;
  localStorage.setItem("leftSize", leftSize);

  calculateLayout();
  setTimeout(
    () => {
      leftContainer.classList.toggle("Hidden", true);
    },
    leftSize ? 0 : 300
  );
});

closeRightButton.addEventListener("click", () => {
  rightSize = 1 - rightSize;
  localStorage.setItem("rightSize", rightSize);

  calculateLayout();
  setTimeout(
    () => {
      rightContainer.classList.toggle("Hidden", true);
    },
    rightSize ? 0 : 300
  );
});

// If the mouse holds on the left side of the screen, open the left container
document.addEventListener("mousemove", (e) => {
  if (e.clientX < 10) {
    if (!leftTimer) {
      leftTimer = setTimeout(() => {
        leftSize = 1;
        localStorage.setItem("leftSize", leftSize);

        calculateLayout();
        setTimeout(() => {
          leftContainer.classList.toggle("Hidden", false);
        }, 300);
      }, 200);
    }
  } else {
    clearTimeout(leftTimer);
    leftTimer = null;
  }
});

// If the mouse holds on the right side of the screen, open the right container
document.addEventListener("mousemove", (e) => {
  if (e.clientX > window.innerWidth - 10) {
    if (!rightTimer) {
      rightTimer = setTimeout(() => {
        rightSize = 1;
        localStorage.setItem("rightSize", rightSize);

        calculateLayout();
        setTimeout(() => {
          rightContainer.classList.toggle("Hidden", false);
        }, 300);
      }, 200);
    }
  } else {
    clearTimeout(rightTimer);
    rightTimer = null;
  }
});
