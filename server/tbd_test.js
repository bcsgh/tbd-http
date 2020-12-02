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