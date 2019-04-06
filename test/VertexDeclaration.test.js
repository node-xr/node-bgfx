const { VertexDeclaration } = require('../lib/vertex');
const helpers = require('./vertex.helpers');

describe('VertexDeclaration', () => {
  describe('#constructor', () => {
    it('handles valid spec', () => {
      const decl = new VertexDeclaration(helpers.spec);
      expect(decl).toBeDefined();
    });

    it('rejects invalid attribute', () => {
      expect(() => {
        const decl = new VertexDeclaration(helpers.specInvalidAttr);
        expect(decl).toBeDefined();
      }).toThrow();
    });

    it('rejects invalid type', () => {
      expect(() => {
        const decl = new VertexDeclaration(helpers.specInvalidType);
        expect(decl).toBeDefined();
      }).toThrow();
    });
  });

  describe('#fromData', () => {
    // TODO: fill this in.
  });
});
