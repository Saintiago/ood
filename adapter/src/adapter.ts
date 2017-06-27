import * as graphics_lib_pro from './graphics_lib_pro';
import * as stream from './lib/output_stream';
import * as modern_graphics_lib_pro from './modern_graphics_lib_pro';

function uint32ToRGBA(color: number) {
    const redMask = 0xFF0000;
    const greenMask = 0xFF00;
    const blueMask = 0xFF;

    const r = ((color & redMask) >> 16) / 255;
    const g = ((color & greenMask) >> 8) / 255;
    const b = (color & blueMask) / 255;

    return new modern_graphics_lib_pro.CRGBAColor(r, g, b);
}

export class CModernGraphicsRendererAdapter implements graphics_lib_pro.ICanvas {

    private p1: modern_graphics_lib_pro.CPoint;
    private color: modern_graphics_lib_pro.CRGBAColor;

    constructor(private renderer: modern_graphics_lib_pro.CModernGraphicsRenderer) {}

    public SetColor(color: number) {
        this.color = uint32ToRGBA(color);
    }

    public MoveTo(x: number, y: number) {
        this.p1 = new modern_graphics_lib_pro.CPoint(x, y);
    }

    public LineTo(x: number, y: number) {
        const p2 = new modern_graphics_lib_pro.CPoint(x, y);
        this.renderer.DrawLine(this.p1, p2, this.color);
        this.p1 = p2;
    }

    public Destructor() {
        this.renderer.Destructor();
    }
}

export class CModernGraphicsRendererAdapterClass
    extends modern_graphics_lib_pro.CModernGraphicsRenderer
    implements graphics_lib_pro.ICanvas {

    private p1: modern_graphics_lib_pro.CPoint;
    private color: modern_graphics_lib_pro.CRGBAColor;

    constructor(out: stream.Cout) {
        super(out);
    }

    public SetColor(color: number) {
        this.color = uint32ToRGBA(color);
    }

    public MoveTo(x: number, y: number) {
        this.p1 = new modern_graphics_lib_pro.CPoint(x, y);
    }

    public LineTo(x: number, y: number) {
        const p2 = new modern_graphics_lib_pro.CPoint(x, y);
        this.DrawLine(this.p1, p2, this.color);
        this.p1 = p2;
    }
}
