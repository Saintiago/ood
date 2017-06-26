import * as graphics_lib from './graphics_lib';
import * as stream from './lib/output_stream';
import * as modern_graphics_lib from './modern_graphics_lib';

export class CModernGraphicsRendererAdapter implements graphics_lib.ICanvas {

    private p1: modern_graphics_lib.CPoint;

    constructor(private renderer: modern_graphics_lib.CModernGraphicsRenderer) {}

    public MoveTo(x: number, y: number) {
        this.p1 = new modern_graphics_lib.CPoint(x, y);
    }

    public LineTo(x: number, y: number) {
        const p2 = new modern_graphics_lib.CPoint(x, y);
        this.renderer.BeginDraw();
        this.renderer.DrawLine(this.p1, p2);
        this.renderer.EndDraw();
    }
}

export class CModernGraphicsRendererAdapterClass
    extends modern_graphics_lib.CModernGraphicsRenderer
    implements graphics_lib.ICanvas {

    private p1: modern_graphics_lib.CPoint;

    constructor(out: stream.Cout) {
        super(out);
    }

    public MoveTo(x: number, y: number) {
        this.p1 = new modern_graphics_lib.CPoint(x, y);
    }

    public LineTo(x: number, y: number) {
        const p2 = new modern_graphics_lib.CPoint(x, y);
        this.BeginDraw();
        this.DrawLine(this.p1, p2);
        this.EndDraw();
    }
}
