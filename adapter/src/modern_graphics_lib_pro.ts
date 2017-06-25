import * as stream from './lib/output_stream';

export class CPoint {
    constructor(public x: number, public y: number) {}
}

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
export class CRGBAColor {
    constructor(public r: number, public g: number, public b: number, public a: number) {}
}

// Класс для современного рисования графики
export class CModernGraphicsRenderer {

    private drawing: boolean = false;

    constructor(private out: stream.IOutputStream) {
    }

    public destructor() {
        if (this.drawing) {
            this.EndDraw();
        }
    }

    public BeginDraw() {
        if (this.drawing) {
            throw Error("Drawing has already begun");
        }

        this.out.write('<draw>');
        this.drawing = true;
    }

    // Выполняет рисование линии
    public DrawLine(start: CPoint, end: CPoint) {
        // TODO: выводит в output инструкцию для рисования линии в виде
        // <line fromX="3" fromY="5" toX="5" toY="17">
        //   <color r="0.35" g="0.47" b="1.0" a="1.0" />
        // </line>
        // Можно вызывать только между BeginDraw() и EndDraw()
    }

    public EndDraw() {
        if (!this.drawing) {
            throw Error("Drawing has not been started");
        }
        this.out.write('</draw>');
        this.drawing = false;
    }
}