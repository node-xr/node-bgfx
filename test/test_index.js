const chai = require("chai");
const dirtyChai = require("dirty-chai");
const expect = require("chai").expect;
const bgfx = require("../index");

chai.use(dirtyChai);

describe("bgfx", () => {
  expect(bgfx).toBeDefined();
  // TODO: add unit tests per function.
});
