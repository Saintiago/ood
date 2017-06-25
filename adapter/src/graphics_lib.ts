export interface ICanvas {
    MoveTo: (x: number, y: number) => void;
    LineTo: (x: number, y: number) => void;
}

export class CCanvas implements ICanvas {
    public  MoveTo(x: number, y: number) {
        console.log('MoveTo (' + x + ', ' + y + ')');
    }
    public  LineTo(x: number, y: number) {
        console.log('LineTo (' + x + ', ' + y + ')');
    }
}

