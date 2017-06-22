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

/*import * as React from 'react';
 import * as enzyme from 'enzyme';
 import Hello from './Hello';

 it('renders the correct text when no enthusiasm level is given', () => {
 const hello = enzyme.shallow(<Hello name='Daniel' />);
 expect(hello.find(".greeting").text()).toEqual('Hello Daniel!')
 });

 it('renders the correct text with an explicit enthusiasm of 1', () => {
 const hello = enzyme.shallow(<Hello name='Daniel' enthusiasmLevel={1}/>);
 expect(hello.find(".greeting").text()).toEqual('Hello Daniel!')
 });

 it('renders the correct text with an explicit enthusiasm level of 5', () => {
 const hello = enzyme.shallow(<Hello name='Daniel' enthusiasmLevel={5} />);
 expect(hello.find(".greeting").text()).toEqual('Hello Daniel!!!!!');
 });

 it('throws when the enthusiasm level is 0', () => {
 expect(() => {
 enzyme.shallow(<Hello name='Daniel' enthusiasmLevel={0} />);
 }).toThrow();
 });

 it('throws when the enthusiasm level is negative', () => {
 expect(() => {
 enzyme.shallow(<Hello name='Daniel' enthusiasmLevel={-1} />);
 }).toThrow();
 });*/
