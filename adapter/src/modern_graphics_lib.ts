import * as stream from './lib/output_stream';

export class CPoint {
    constructor(public x: number, public y: number) {}
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
        if (!this.drawing) {
            throw Error("DrawLine is allowed between BeginDraw()/EndDraw() only");
        }
        this.out.write(
            '<line fromX="' + start.x + '" fromY="' + start.y + '" toX="' + end.x + '" toY="' + end.y + '"/>');
    }

    // Этот метод должен быть вызван в конце рисования
    public EndDraw() {
        if (!this.drawing) {
            throw Error("Drawing has not been started");
        }
        this.out.write('</draw>');
        this.drawing = false;
    }
}
