const helpers = require('./vertex.helpers');
const { VertexDeclaration } = require('../vertex');

describe('VertexDeclaration', () => {
  describe('#constructor', () => {
    it('handles enum spec', () => {
      const decl = new VertexDeclaration(helpers.specEnum);
      expect(decl).toBeDefined();
    });

    it('handles string spec', () => {
      const decl = new VertexDeclaration(helpers.specStr);
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
    it('handles enum spec', () => {
      fail();
    });

    it('handles string spec', () => {
      fail();
    });

    it('handles multiple defaults', () => {
      fail();
    });
  });
});
