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

const CLASS_MIN_WIDTH = "min_width";
/**
 * The entry point.
 */
export function Main() {
  fetch("/preamble.tbd").then(async function(response) {
    const output = document.getElementById("preamble");
    if (output) output.innerText = await response.text();
  });

  fetch("/units").then(async function(r) {
    const o = document.getElementById("units") as HTMLPreElement;
    if (o) ProcessUnits(r, o);
  });

  const submit_script = document.getElementById("submit_script");
  if (submit_script) submit_script.onclick = PostRequest;
}

/**
 * Process units responce.
 */
async function ProcessUnits(response: Response, output: HTMLPreElement) {
  output.innerText = "";

  let table = document.createElement("table");
  output.appendChild(table);
  table.style.borderCollapse = "collapse";

  // Build column headers.
  let th = document.createElement("thead");
  table.appendChild(th);
  th.appendChild(document.createElement("td")).innerText = "Name";
  th.appendChild(document.createElement("td")).innerText = "Scale";
  th.appendChild(document.createElement("td")).innerText = "m";
  th.appendChild(document.createElement("td")).innerText = "kg";
  th.appendChild(document.createElement("td")).innerText = "s";
  th.appendChild(document.createElement("td")).innerText = "A";
  th.appendChild(document.createElement("td")).innerText = "K";
  th.appendChild(document.createElement("td")).innerText = "mol";
  th.appendChild(document.createElement("td")).innerText = "cd";

  const json = await response.json();
  const /** @type{Object<string, !Array<!string>>}*/ classes = json["types"];
  const /** @type{Object<string, !Object<string, !number>>}*/ units = json["units"];

  // Build body.
  let tb = table.appendChild(document.createElement("tbody"));
  for (let v in classes) {
    let first = true;
    const types = classes[v];

    for (let t of types) {
      const unit = units[t];
      if (!unit) continue;

      let r = document.createElement("tr");
      tb.appendChild(r);

      r.appendChild(document.createElement("td")).innerText = t;
      r.appendChild(document.createElement("td")).innerText = unit["scale"];

      if (first) {
        first = false;
        r.classList.add("firstrow");

        // Extra stuff for the first of each class of unit.
        const m    = r.appendChild(document.createElement("td"));
        const kg   = r.appendChild(document.createElement("td"));
        const s    = r.appendChild(document.createElement("td"));
        const A    = r.appendChild(document.createElement("td"));
        const K    = r.appendChild(document.createElement("td"));
        const mol  = r.appendChild(document.createElement("td"));
        const cd   = r.appendChild(document.createElement("td"));
        const type = r.appendChild(document.createElement("td"));

        m.classList.add(CLASS_MIN_WIDTH);
        kg.classList.add(CLASS_MIN_WIDTH);
        s.classList.add(CLASS_MIN_WIDTH);
        A.classList.add(CLASS_MIN_WIDTH);
        K.classList.add(CLASS_MIN_WIDTH);
        mol.classList.add(CLASS_MIN_WIDTH);
        cd.classList.add(CLASS_MIN_WIDTH);

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
  const input_script =
      document.getElementById("input_script")! as HTMLTextAreaElement;

  fetch("/json", {method: "POST", body: input_script.value})
      .then(ProcessResponce);
}

interface RequestRow {
  name?: string,
  value?: number,
  unit?: string,
};

interface RequestResult {
  values?: Array<RequestRow>,
  errors?: string,
};

/**
 * Process server responce.
 */
async function ProcessResponce(response: Response) {
  const output = document.getElementById("output")! as HTMLSpanElement;

  if (response.ok) {
    let json = await response.json() as RequestResult;
    FillTable(output, json);
  } else {
    let json = JSON.parse(await response.text()) as RequestResult;
    output.innerHTML = "";
    output.appendChild(document.createElement("pre")).innerText =
        json.errors ?? "Unknown error";
  }
}

/**
 * Render success results as a table
 */
function FillTable(output: HTMLElement, result: RequestResult) {
  output.innerHTML = "";
  let t = output.appendChild(document.createElement("table"));
  t.border = "1";
  {
    let r = t.appendChild(document.createElement("thead"))
                .appendChild(document.createElement("tr"));
    r.appendChild(document.createElement("th")).innerText = "Name ";
    r.appendChild(document.createElement("th")).innerText = "Value ";
    r.appendChild(document.createElement("th")).innerText = "Units ";
  }
  let tb = t.appendChild(document.createElement("tbody"));

  for (let v of result.values ?? []) {
    let r = tb.appendChild(document.createElement("tr"));
    let name = r.appendChild(document.createElement("td"));
    let value = r.appendChild(document.createElement("td"));
    let unit = r.appendChild(document.createElement("td"));
    if (v.name) name.innerText = v.name;
    if (v.value) value.innerText = `${v.value}`;
    if (v.unit) unit.innerText = v.unit;
  }
}
