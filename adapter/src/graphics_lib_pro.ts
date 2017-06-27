// Холст для рисования

export interface ICanvas {
    SetColor: (color: number) => void;
    MoveTo: (x: number, y: number) => void;
    LineTo: (x: number, y: number) => void;
    Destructor: () => void;
}

// Реализация холста для рисования
export class CCanvas implements ICanvas {

    public SetColor(color: number) {
        console.log('SetColor (#' + color.toString(16) + ')');
    }

    public  MoveTo(x: number, y: number) {
        console.log('MoveTo (' + x + ', ' + y + ')');
    }

    public  LineTo(x: number, y: number) {
        console.log('LineTo (' + x + ', ' + y + ')');
    }

    public Destructor() {
        return;
    }
}
