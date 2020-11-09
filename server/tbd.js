goog.module('TBD.Main');

const {DomHelper} = goog.require("goog.dom");

/**
 * The entry point.
 */
function Main() {
  const dom = new DomHelper();

  const submit_script = /** @type{HTMLButtonElement}*/(dom.getElement("submit_script"));
  submit_script.onclick = function() {
    const input_script = /** @type{HTMLTextAreaElement}*/(dom.getElement("input_script"));
    fetch('/json', {method: 'POST', body: input_script.value})
      .then(response => response.json())
      .then(function(/** Object*/data) {
        const output = /** @type{HTMLSpanElement}*/(dom.getElement("output"));
        output.innerText = JSON.stringify(data);
      });
  };
}

exports = Main;
