const bgfx = require('bindings')('bgfx');
const {
  VertexArray,
  ATTRIB_SIZE,
  ATTRIB_TYPEDARRAY,
} = require('../../lib/vertex');
const helpers = require('./vertex.helpers');

describe('VertexArray', () => {
  let mem;

  beforeAll(() => {
    mem = new ArrayBuffer(16 * 100);
  });

  describe('ATTRIB_SIZE', () => {
    it('has an entry for each bgfx attribute type', () => {
      for (const type in bgfx.ATTRIB_TYPE) {
        expect(ATTRIB_SIZE).toHaveProperty(type);
      }
    });
  });

  describe('ATTRIB_TYPEDARRAY', () => {
    it('has an entry for each bgfx attribute type', () => {
      for (const type in bgfx.ATTRIB_TYPE) {
        expect(ATTRIB_TYPEDARRAY).toHaveProperty(type);
      }
    });
  });

  describe('#constructor', () => {
    it('works with internal buffer', () => {
      const arr = new VertexArray(helpers.spec, 100);
      expect(arr).toBeDefined();
    });

    it('works with external buffer', () => {
      const arr = new VertexArray(helpers.spec, 100, mem);
      expect(arr).toBeDefined();
    });

    it('rejects invalid sizes', () => {
      expect(() => {
        new VertexArray(helpers.spec, -1);
      }).toThrow();

      expect(() => {
        new VertexArray(helpers.spec, 99, mem);
      }).toThrow();
    });
  });

  describe('#get', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.spec, 100);
    });

    it('accesses an element', () => {
      const element = arr.get(0);
      expect(element.POSITION).toBeDefined();
      expect(element.COLOR_0).toBeDefined();
    });

    it('modifies an element via view', () => {
      const element = arr.get(3);

      element.POSITION = [5, 6, 7];
      expect(element.POSITION).toEqual(new Float32Array([5, 6, 7]));

      element.COLOR_0 = [10, 11, 12, 13];
      expect(element.COLOR_0).toEqual(new Uint8Array([10, 11, 12, 13]));
    });
  });

  describe('#set', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.spec, 100);
    });

    it('rejects setting undefined elements', () => {
      expect(() => arr.set(4, {})).toThrow();
    });

    it('sets element from an object', () => {
      arr.set(4, {
        POSITION: [0.1, 0.2, 0.3],
        COLOR_0: [255, 254, 253, 0],
      });

      expect(arr.get(4).POSITION).toEqual(new Float32Array([0.1, 0.2, 0.3]));
      expect(arr.get(4).COLOR_0).toEqual(new Uint8Array([255, 254, 253, 0]));
    });
  });

  describe('#operator[]', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.spec, 100);
    });

    it('accesses an element', () => {
      const element = arr[0];
      expect(element.POSITION).toBeDefined();
      expect(element.COLOR_0).toBeDefined();
    });

    it('modifies an element via view', () => {
      const element = arr[3];

      element.POSITION = [5, 6, 7];
      expect(arr[3].POSITION).toEqual(new Float32Array([5, 6, 7]));

      element.COLOR_0 = [10, 11, 12, 13];
      expect(arr[3].COLOR_0).toEqual(new Uint8Array([10, 11, 12, 13]));
    });

    it('rejects setting undefined elements', () => {
      expect(() => {
        arr[0] = {};
      }).toThrow();
    });

    it('sets element from an object', () => {
      arr[4] = { POSITION: [0.1, 0.2, 0.3], COLOR_0: [0xff, 0xff, 0xff, 0x00] };
      arr.set(4, {
        POSITION: [0.1, 0.2, 0.3],
        COLOR_0: [255, 253, 254, 0],
      });
      expect(arr[4].POSITION).toEqual(new Float32Array([0.1, 0.2, 0.3]));
      expect(arr[4].COLOR_0).toEqual(new Uint8Array([255, 253, 254, 0]));
    });
  });

  describe('#iterator', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.spec, 3);
      arr[0] = { POSITION: [0.1, 0.2, 0.3], COLOR_0: [255, 254, 253, 252] };
      arr[1] = { POSITION: [0.3, 0.4, 0.5], COLOR_0: [245, 244, 243, 242] };
      arr[2] = { POSITION: [0.6, 0.7, 0.8], COLOR_0: [235, 234, 233, 232] };
    });

    it('works with for..of', () => {
      let i = 0;
      for (const elem of arr) {
        switch (i++) {
          case 0:
            expect(elem).toMatchObject({
              POSITION: new Float32Array([0.1, 0.2, 0.3]),
              COLOR_0: new Uint8Array([255, 254, 253, 252]),
            });
            break;
          case 1:
            expect(elem).toMatchObject({
              POSITION: new Float32Array([0.3, 0.4, 0.5]),
              COLOR_0: new Uint8Array([245, 244, 243, 242]),
            });
            break;
          case 2:
            expect(elem).toMatchObject({
              POSITION: new Float32Array([0.6, 0.7, 0.8]),
              COLOR_0: new Uint8Array([235, 234, 233, 232]),
            });
            break;
        }
      }
    });
  });

  describe('#clone', () => {
    it('works with internal buffers', () => {
      const arr = new VertexArray(helpers.spec, 100);
      const clone = arr.clone();
      expect(clone).toMatchObject({
        length: 100,
      });
    });

    it('works with external buffers', () => {
      const arr = new VertexArray(helpers.spec, 100, mem);
      const clone = arr.clone();
      expect(clone).toMatchObject({
        length: 100,
      });
    });

    it('makes a copy of the buffer', () => {
      const arr = new VertexArray(helpers.spec, 100);
      const clone = arr.clone();

      const arrView1 = new Int32Array(arr._data);
      const arrView2 = new Int32Array(arr._data);
      const cloneView = new Int32Array(clone._data);

      arrView1[0] = 0xff00;

      expect(arrView2[0]).toEqual(0xff00);
      expect(cloneView[0]).toEqual(0);
    });
  });
});
