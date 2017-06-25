export interface IOutputStream {
    write: (str: string) => void;
}

export class Cout implements IOutputStream {
    public write(str: string) {
        console.log(str);
    }
}
