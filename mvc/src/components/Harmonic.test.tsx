import Harmonic from './Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

it('can be constructed', () => {
    new Harmonic(1, 1, 1, harmonicFunctionType.Sin);
});

/*it('can calculate Y for given X', () => {
    let testHarmonic = new Harmonic(1, 1, 1, harmonicFunctionType.Sin);
    expect(testHarmonic.getY(0)).toBeCloseTo(0.841);
    expect(testHarmonic.getY(1)).toBeCloseTo(0.909);
    expect(testHarmonic.getY(-1)).toBe(0);
});*/
