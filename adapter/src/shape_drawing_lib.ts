import * as graphics_lib from './graphics_lib';

export interface IPoint {
    x: number;
    y: number;
}

export interface ICanvasDrawable {
    Draw: (canvas: graphics_lib.ICanvas) => void;
}

export class CTriangle implements ICanvasDrawable {

    constructor(p1: IPoint, p2: IPoint, p3: IPoint) {
        // TODO: написать код конструктора
    }

    public Draw(canvas: graphics_lib.ICanvas) {
        // TODO: написать код рисования треугольника на холсте
    }

    // TODO: дописать приватную часть
}

export class CRectangle implements ICanvasDrawable {
    constructor(leftTop: IPoint, width: number, height: number) {
        // TODO: написать код конструктора
    }

    public Draw(canvas: graphics_lib.ICanvas) {
        // TODO: написать код рисования прямоугольника на холсте
    }

    // TODO: дописать приватную часть
}

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
export class CCanvasPainter {
    constructor(canvas: graphics_lib.ICanvas) {
        // TODO: дописать конструктор класса
    }

    public Draw(drawable: ICanvasDrawable) {
        // TODO: дописать код рисования ICanvasDrawable на canvas, переданном в конструктор
    }

    // TODO: дописать приватную часть
}
