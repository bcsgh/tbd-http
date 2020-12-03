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

goog.module('TBD.Main_test');
goog.setTestOnly('TBD.Main_test');

var Main = goog.require('TBD.Main');
var testSuite = goog.require('goog.testing.testSuite');

goog.require('goog.testing.jsunit');

testSuite({
  testFillTableEmpty: function() {
    let output = /** @type{HTMLSpanElement} */(document.createElement("span"));
    output.innerText = "mallory";

    let result = {"values": []};

    Main.impl.FillTable(output, result);

    assertEquals(output.innerText, "Name Value Units ");
  },

  testFillTableEmptyItems: function() {
    let output = /** @type{HTMLSpanElement} */(document.createElement("span"));
    output.innerText = "mallory";

    let result = {"values": [{}, {}]};

    Main.impl.FillTable(output, result);

    assertEquals(output.innerText, "Name Value Units ");
  },

  testFillTablePartialItems: function() {
    let output = /** @type{HTMLSpanElement} */(document.createElement("span"));
    output.innerText = "mallory";

    let result = {"values": [{"unit": "[x]"}, {"value":"123."}, {"name":"bob"}]};

    Main.impl.FillTable(output, result);

    assertEquals(output.innerText, "Name Value Units [x]123.bob");
  },

  testFillTableFullItems: function() {
    let output = /** @type{HTMLSpanElement} */(document.createElement("span"));
    output.innerText = "mallory";

    let result = {"values": [
      {"name":"alice", "value":"123.", "unit": "[x]"},
      {"name":"bob",   "value":"45.6", "unit": "[y]"},
      {"name":"trent", "value":"7.89", "unit": "[z]"},
    ]};

    Main.impl.FillTable(output, result);

    assertEquals(output.innerText,
                 "Name Value Units alice123.[x]bob45.6[y]trent7.89[z]");
  },
});