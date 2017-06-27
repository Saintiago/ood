import * as stream from './lib/output_stream';

export class CPoint {
    constructor(public x: number, public y: number) {}
}

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
export class CRGBAColor {
    constructor(public r: number = 0,
                public g: number = 0,
                public b: number = 0,
                public a: number = 1) {}
}

// Класс для современного рисования графики
export class CModernGraphicsRenderer {

    private drawing: boolean = false;

    constructor(private out: stream.IOutputStream) {
        this.BeginDraw();
    }

    public Destructor() {
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
    public DrawLine(start: CPoint, end: CPoint, color: CRGBAColor = new CRGBAColor()) {
        if (!this.drawing) {
            throw Error("DrawLine is allowed between BeginDraw()/EndDraw() only");
        }

        this.out.write(
            '<line fromX="' + start.x + '" fromY="' + start.y + '" toX="' + end.x + '" toY="' + end.y + '">');

        this.out.write('<color ' +
            'r="' + color.r.toFixed(2) + '" ' +
            'g="' + color.g.toFixed(2) + '" ' +
            'b="' + color.b.toFixed(2) + '" ' +
            'a="' + color.a.toFixed(2) + '" />');

        this.out.write('</line>');
    }

    public EndDraw() {
        if (!this.drawing) {
            throw Error("Drawing has not been started");
        }
        this.out.write('</draw>');
        this.drawing = false;
    }
}
