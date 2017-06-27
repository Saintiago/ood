import * as adapter from '../adapter';
import * as graphics_lib_pro from '../graphics_lib_pro';
import * as stream from '../lib/output_stream';
import * as modern_graphics_lib_pro from '../modern_graphics_lib_pro';
import * as shape_drawing_lib from '../shape_drawing_lib';

class TestCout implements stream.IOutputStream {

    public static buffer: string = '';

    public static reset() {
        TestCout.buffer = '';
    }

    public write(str: string) {
        TestCout.buffer += str;
    }
}

function testAdapterDrawLine(adapter: graphics_lib_pro.ICanvas) {
    const p1 = {x: 0, y: 0};
    const p2 = {x: 1, y: 1};
    const color = {r: 0, g: 0, b: 0, a: 1};

    adapter.MoveTo(p1.x, p1.y);
    adapter.LineTo(p2.x, p2.y);
    adapter.Destructor();
    expect(TestCout.buffer).toBe(
        '<draw>' +
            '<line fromX="' + p1.x + '" fromY="' + p1.y + '" toX="' + p2.x + '" toY="' + p2.y + '">' +
                '<color ' +
                'r="' + color.r.toFixed(2) + '" ' +
                'g="' + color.g.toFixed(2) + '" ' +
                'b="' + color.b.toFixed(2) + '" ' +
                'a="' + color.a.toFixed(2) + '" />' +
            '</line>' +
        '</draw>');
}

function testAdapterDrawTriangle(adapter: graphics_lib_pro.ICanvas) {
    const triangle = new shape_drawing_lib.CTriangle(
        { x: 10, y: 15 }, { x: 100, y: 200 }, { x: 150, y: 250 }, 0xFFFFFF);
    const painter = new shape_drawing_lib.CCanvasPainter(adapter);

    painter.Draw(triangle);
    expect(TestCout.buffer).toBe(
        '<draw>' +
            '<line fromX="10" fromY="15" toX="100" toY="200">' +
                '<color r="1.00" g="1.00" b="1.00" a="1.00" />' +
            '</line>' +
            '<line fromX="100" fromY="200" toX="150" toY="250">' +
                '<color r="1.00" g="1.00" b="1.00" a="1.00" />' +
            '</line>' +
            '<line fromX="150" fromY="250" toX="10" toY="15">' +
                '<color r="1.00" g="1.00" b="1.00" a="1.00" />' +
            '</line>' +
        '</draw>');
}

describe('CModernGraphicsRenderer', () => {
    it('can draw line', () => {
        const testCout = new TestCout();
        const renderer = new modern_graphics_lib_pro.CModernGraphicsRenderer(testCout);
        const rendererAdapter = new adapter.CModernGraphicsRendererAdapter(renderer);
        testAdapterDrawLine(rendererAdapter);
    });
    it('can draw triangle', () => {
        const testCout = new TestCout();
        TestCout.reset();
        const renderer = new modern_graphics_lib_pro.CModernGraphicsRenderer(testCout);
        const rendererAdapter = new adapter.CModernGraphicsRendererAdapter(renderer);
        testAdapterDrawTriangle(rendererAdapter);
    });
});

describe('CModernGraphicsRendererClass', () => {
    it('can draw line', () => {
        const testCout = new TestCout();
        TestCout.reset();
        const rendererAdapter = new adapter.CModernGraphicsRendererAdapterClass(testCout);
        testAdapterDrawLine(rendererAdapter);
    });
    it('can draw triangle', () => {
        const testCout = new TestCout();
        TestCout.reset();
        const rendererAdapter = new adapter.CModernGraphicsRendererAdapterClass(testCout);
        testAdapterDrawTriangle(rendererAdapter);
    });
});
