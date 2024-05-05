import $ from "jquery";
import alertHtml from "../components/notifications/index.html";

const alertContainer = $("#alert-container")?.[0];

const iconMap = {
  info: "fa-info-circle",
  success: "fa-thumbs-up",
  warning: "fa-exclamation-triangle",
  error: "ffa fa-exclamation-circle",
};

/**
 * Create an alert
 * @param {string} title 
 * @param {string} message 
 * @param {string} type - success, warning, error
 */
export const createAlert = (title, message, type) => {
  $.ajax({
    url: alertHtml,
    success: (data) => {
      const [alert] = $(data);

      // Return if the alert cannot be created, usefull when a redirect is made
      if (!alertContainer || !alert || !alert.classList) return;

      // Add the type class to the alert
      alert.classList.add(
        `Alert${type.charAt(0).toUpperCase() + type.slice(1)}`
      );

      // Replace values in innerHTML
      alert.innerHTML = alert.innerHTML
        .replace(/{{title}}/g, title)
        .replace(/{{content}}/g, message)
        .replace(/{{icon_classes}}/g, iconMap[type]);

      // Get the close button
      const closeBtn = alert.getElementsByClassName("AlertClose")?.[0];
      closeBtn?.addEventListener("click", () => {
        alert.remove();
      });

      // Append the alert to the container
      alertContainer.append(alert);

      // Remove the alert after 5 seconds
      setTimeout(() => {
        alert.remove();
      }, 5000);
    },
  });
};
