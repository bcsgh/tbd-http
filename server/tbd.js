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
      .then(async function(response) {
        const output = /** @type{HTMLSpanElement}*/(dom.getElement("output"));
        console.log(response.ok);
        if (response.ok) {
          let json = await response.json();
          FillTable(output, json);
        } else {
          let json = JSON.parse(await response.text());
          output.innerHTML = "";
          output.appendChild(document.createElement("pre")).innerText = json["errors"];
        }
      });
  };
}

/**
 * Render success results as a table
 * @param {HTMLElement} output The node to fill.
 * @param {*} result The node to fill.
 */
function FillTable(output, result) {
  output.innerHTML = "";
  let t = output.appendChild(document.createElement("table"));
  t.border = 1;
  let tb = t.appendChild(document.createElement("tbody"));

  for (let /** @type {*} */ v of result["values"]) {
    let r = tb.appendChild(document.createElement("tr"));
    let name = r.appendChild(document.createElement("td"));
    let value = r.appendChild(document.createElement("td"));
    let unit = r.appendChild(document.createElement("td"));
    if ("name" in v) name.innerText = v["name"];
    if ("value" in v) value.innerText = v["value"];
    if ("unit" in v) unit.innerText = v["unit"];
  }
}

exports = Main;
