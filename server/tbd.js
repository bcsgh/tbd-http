// Copyright (c) 2020, Benjamin Shropshire,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

goog.module('TBD.Main');

const {DomHelper, TagName, createDom} = goog.require("goog.dom");

const CLASS_MIN_WIDTH = "min_width";
/**
 * The entry point.
 */
function Main() {
  const dom = new DomHelper();

  fetch('/preamble.tbd')
    .then(async function(response) {
      const output = /** @type{HTMLPreElement}*/(dom.getElement("preamble"));
      output.innerText = await response.text();
    });

  fetch('/units')
    .then(async function(r) {
      const o = /** @type{HTMLPreElement}*/(dom.getElement("units"));
      ProcessUnits(r, o);
    });

  const submit_script = /** @type{HTMLButtonElement}*/(dom.getElement("submit_script"));
  submit_script.onclick = PostRequest;
}

/**
 * Process units responce.
 * @param {Response} response Fetch response.
 * @param {HTMLPreElement} output Where to render;
 */
async function ProcessUnits(response, output) {
  output.innerText = "";

  let table = createDom(TagName.TABLE);
  output.appendChild(table);
  table.style.borderCollapse = "collapse";

  // Build column headers.
  let th = createDom(TagName.THEAD);
  table.appendChild(th);
  th.appendChild(createDom(TagName.TD)).innerText = "Name";
  th.appendChild(createDom(TagName.TD)).innerText = "Scale";
  th.appendChild(createDom(TagName.TD)).innerText = "m";
  th.appendChild(createDom(TagName.TD)).innerText = "kg";
  th.appendChild(createDom(TagName.TD)).innerText = "s";
  th.appendChild(createDom(TagName.TD)).innerText = "A";
  th.appendChild(createDom(TagName.TD)).innerText = "K";
  th.appendChild(createDom(TagName.TD)).innerText = "mol";
  th.appendChild(createDom(TagName.TD)).innerText = "cd";

  const json = await response.json();
  const /** @type{Object<string, !Array<!string>>}*/ classes = json["types"];
  const /** @type{Object<string, !Object<string, !number>>}*/ units = json["units"];

  // Build body.
  let tb = table.appendChild(createDom(TagName.TBODY));
  for (let v in classes) {
    let first = true;
    const types = classes[v];

    for (let t of types) {
      const unit = units[t];
      if (!unit) continue;

      let r = createDom(TagName.TR);
      tb.appendChild(r);

      r.appendChild(createDom(TagName.TD)).innerText = t;
      r.appendChild(createDom(TagName.TD)).innerText = unit["scale"];

      if (first) {
        first = false;
        r.classList.add("firstrow");

        // Extra stuff for the first of each class of unit.
        const m    = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const kg   = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const s    = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const A    = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const K    = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const mol  = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const cd   = r.appendChild(createDom(TagName.TD, CLASS_MIN_WIDTH));
        const type = r.appendChild(createDom(TagName.TD));

        if (unit["L"])   m.innerText = unit["L"];
        if (unit["M"])  kg.innerText = unit["M"];
        if (unit["T"])   s.innerText = unit["T"];
        if (unit["I"])   A.innerText = unit["I"];
        if (unit["K"])   K.innerText = unit["K"];
        if (unit["N"]) mol.innerText = unit["N"];
        if (unit["J"])  cd.innerText = unit["J"];
        type.innerText = v;
      }
    }
  }
}

/**
 * Process the user input server side.
 */
function PostRequest() {
  const dom = new DomHelper();
  const input_script = /** @type{HTMLTextAreaElement}*/(dom.getElement("input_script"));

  fetch('/json', {method: 'POST', body: input_script.value})
    .then(ProcessResponce);
}

/**
 * Process server responce.
 * @param {Response} response Fetch response.
 */
async function ProcessResponce(response) {
  const dom = new DomHelper();
  const output = /** @type{HTMLSpanElement}*/(dom.getElement("output"));

  if (response.ok) {
    let json = await response.json();
    FillTable(output, json);
  } else {
    let json = JSON.parse(await response.text());
    output.innerHTML = "";
    output.appendChild(document.createElement("pre")).innerText = json["errors"];
  }
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
  {
    let r = t.appendChild(document.createElement("thead"))
             .appendChild(document.createElement("tr"));
    r.appendChild(document.createElement("th")).innerText = "Name ";
    r.appendChild(document.createElement("th")).innerText = "Value ";
    r.appendChild(document.createElement("th")).innerText = "Units ";
  }
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

exports = {
  Main: Main,
  impl: {
    FillTable: FillTable,
    PostRequest: PostRequest,
    ProcessResponce: ProcessResponce,
    ProcessUnits: ProcessUnits,
  },
};
