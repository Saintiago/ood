import * as adapter from '../adapter';
import * as stream from '../lib/output_stream';
import * as modern_graphics_lib from '../modern_graphics_lib';

class TestCout implements stream.IOutputStream {

    public buffer: string = '';

    public write(str: string) {
        this.buffer += str;
    }
}

describe('CModernGraphicsRenderer', () => {
    const testCout = new TestCout();
    const renderer = new modern_graphics_lib.CModernGraphicsRenderer(testCout);
    const rendererAdapter = new adapter.CModernGraphicsRendererAdapter(renderer);
    const p1 = {x: 0, y: 0};
    const p2 = {x: 1, y: 1};

    it('can draw line', () => {
        rendererAdapter.MoveTo(p1.x, p1.y);
        rendererAdapter.LineTo(p2.x, p2.y);
        expect(testCout.buffer).toBe(
            '<draw><line fromX="' + p1.x + '" fromY="' + p1.y + '" toX="' + p2.x + '" toY="' + p2.y + '"/></draw>');
    });
});

describe('CModernGraphicsRendererClass', () => {
    const testCout = new TestCout();
    const rendererAdapter = new adapter.CModernGraphicsRendererAdapterClass(testCout);
    const p1 = {x: 0, y: 0};
    const p2 = {x: 1, y: 1};

    it('can draw line', () => {
        rendererAdapter.MoveTo(p1.x, p1.y);
        rendererAdapter.LineTo(p2.x, p2.y);
        expect(testCout.buffer).toBe(
            '<draw><line fromX="' + p1.x + '" fromY="' + p1.y + '" toX="' + p2.x + '" toY="' + p2.y + '"/></draw>');
    });
});
