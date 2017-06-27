import * as graphics_lib_pro from './graphics_lib_pro';

export interface IPoint {
    x: number;
    y: number;
}

export interface ICanvasDrawable {
    Draw: (canvas: graphics_lib_pro.ICanvas) => void;
}

export class CTriangle implements ICanvasDrawable {

    constructor(private p1: IPoint,
                private p2: IPoint,
                private p3: IPoint,
                private color: number = 0) {}

    public Draw(canvas: graphics_lib_pro.ICanvas) {
        canvas.SetColor(this.color);
        canvas.MoveTo(this.p1.x, this.p1.y);
        canvas.LineTo(this.p2.x, this.p2.y);
        canvas.LineTo(this.p3.x, this.p3.y);
        canvas.LineTo(this.p1.x, this.p1.y);
    }
}

export class CRectangle implements ICanvasDrawable {
    constructor(private leftTop: IPoint,
                private width: number,
                private height: number,
                private color: number = 0) {}

    public Draw(canvas: graphics_lib_pro.ICanvas) {
        const lt = this.leftTop;
        const rb = {x: lt.x + this.width, y: lt.y + this.height};
        canvas.SetColor(this.color);
        canvas.MoveTo(lt.x, lt.y);
        canvas.LineTo(rb.x, lt.y);
        canvas.LineTo(rb.x, rb.y);
        canvas.LineTo(lt.x, rb.y);
        canvas.LineTo(lt.x, lt.y);
    }
}

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
export class CCanvasPainter {
    constructor(private canvas: graphics_lib_pro.ICanvas) {}

    public Draw(drawable: ICanvasDrawable) {
        drawable.Draw(this.canvas);
        this.canvas.Destructor();
    }
}
