const bgfx = require('../index');
const helpers = require('./vertex.helpers');
const { VertexArray } = require('../vertex');

describe('VertexArray', () => {
  let mem;

  beforeAll(() => {
    mem = new ArrayBuffer(16 * 100);
  });

  describe('#constructor', () => {
    it('works with internal buffer', () => {
      const arr = new VertexArray(helpers.specEnum, 100);
      expect(arr).toBeDefined();
    });

    it('works with external buffer', () => {
      const arr = new VertexArray(helpers.specEnum, 100, mem);
      expect(arr).toBeDefined();
    });

    it('rejects invalid sizes', () => {
      expect(() => {
        new VertexArray(helpers.specEnum, -1);
      }).toThrow();

      expect(() => {
        new VertexArray(helpers.specEnum, 99, mem);
      }).toThrow();
    });
  });

  describe('#get()', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.specEnum, 100);
    });

    it('can access an element', () => {
      const element = arr.get(0);
      expect(element['POSITION']).toBeDefined();
      expect(element['COLOR_0']).toBeDefined();
    });

    it('can modify an element', () => {
      const element = arr.get(0);

      element['POSITION'] = [5, 6, 7];
      expect(element['POSITION']).toEqual(new Float32Array([5, 6, 7]));

      element['COLOR_0'] = [10, 11, 12, 13];
      expect(element['COLOR_0']).toEqual(new Uint8Array([10, 11, 12, 13]));
    });
  });

  describe('#operator[]', () => {
    let arr;
    beforeAll(() => {
      arr = new VertexArray(helpers.specEnum, 100);
    });

    it('can access an element', () => {
      const element = arr[0];
      expect(element['POSITION']).toBeDefined();
      expect(element['COLOR_0']).toBeDefined();
    });

    it('can modify an element', () => {
      const element = arr[0];

      element['POSITION'] = [5, 6, 7];
      expect(element['POSITION']).toEqual(new Float32Array([5, 6, 7]));

      element['COLOR_0'] = [10, 11, 12, 13];
      expect(element['COLOR_0']).toEqual(new Uint8Array([10, 11, 12, 13]));
    });
  });

  describe('#clone', () => {
    it('works with internal buffers', () => {
      const arr = new VertexArray(helpers.specEnum, 100);
      const clone = arr.clone();
      expect(clone).toMatchObject({
        length: 100
      });
    });

    it('works with external buffers', () => {
      const arr = new VertexArray(helpers.specEnum, 100, mem);
      const clone = arr.clone();
      expect(clone).toMatchObject({
        length: 100
      });
    });

    it('makes a copy of the buffer', () => {
      const arr = new VertexArray(helpers.specEnum, 100);
      const clone = arr.clone();

      const arrView1 = new Int32Array(arr._mem);
      const arrView2 = new Int32Array(arr._mem);
      const cloneView = new Int32Array(clone._mem);

      arrView1[0] = 0xff00;

      expect(arrView2[0]).toEqual(0xff00);
      expect(cloneView[0]).toEqual(0);
    });
  });
});
