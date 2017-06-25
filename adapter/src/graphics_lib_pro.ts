// Холст для рисования
export interface ICanvas {
    SetColor: (rgbColor: number) => void;
    MoveTo: (x: number, y: number) => void;
    LineTo: (x: number, y: number) => void;
}

// Реализация холста для рисования
export class CCanvas implements ICanvas {

    public SetColor(rgbColor: number) {
        // TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
    }

    public MoveTo(x: number, y: number) {
        // Реализация остается без изменения
    }

    public LineTo(x: number, y: number) {
        // Реализация остается без изменения
    }
}
