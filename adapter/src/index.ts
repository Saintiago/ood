import { createInterface } from 'readline';
import * as app from './app';

const readLine = createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false,
});

readLine.question('Should we use new API (y)?', (userInput) => {

    if ((userInput === "y" || userInput === "Y")) {
        app.PaintPictureOnModernGraphicsRenderer();
    } else {
        app.PaintPictureOnCanvas();
    }

    readLine.close();
});
