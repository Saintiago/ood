import { chartDrawerReducer } from './ChartDrawerReducers';
import * as actions from '../actions/ChartDrawerActions';

import Harmonic from '../components/Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import {ChartDrawerState} from "../types/ChartDrawerState";

function getHarmonicsList() {
    let harmonicsList = [] as Harmonic[];
    harmonicsList.push(new Harmonic(4.5, 23, -1, harmonicFunctionType.Sin));
    harmonicsList.push(new Harmonic(-11, 4, 1, harmonicFunctionType.Cos));
    harmonicsList.push(new Harmonic(1, 1, 3, harmonicFunctionType.Sin));
    return harmonicsList;
}

function getInitialState(): ChartDrawerState {
    let harmonicsList = getHarmonicsList();
    return {
        harmonics: harmonicsList,
        selectedHarmonic: harmonicsList[0],
        tmpHarmonic: new Harmonic(0, 0, 0, harmonicFunctionType.Sin),
        selectedHarmonicIndex: 0,
        addDialogVisible: false,
        tabSelected: 'line'
    };
}

function isHarmonicsEqual(h1: Harmonic, h2: Harmonic): boolean {
    return (
        h1.amplitude === h2.amplitude
        && h1.frequency === h2.frequency
        && h1.phase === h2.phase
        && h1.harmonicFunction === h2.harmonicFunction
    );
}

describe('ChartDrawer reducer ', () => {
    it('can select existing harmonic', () => {
        const state = getInitialState();
        const action = actions.selectHarmonic(1);
        const newState = chartDrawerReducer(state, action);
        const harmonicsList = getHarmonicsList();
        expect(newState.selectedHarmonicIndex).toBe(1);
        expect(isHarmonicsEqual(newState.selectedHarmonic, harmonicsList[1])).toBeTruthy();
    });
    it('can\'t select non existing harmonic', () => {
        const state = getInitialState();
        const action = actions.selectHarmonic(-1);
        expect( function(){chartDrawerReducer(state, action); } ).toThrow(RangeError);
    });
    it('can add harmonic', () => {
        let state = getInitialState();
        const newHarmonic = new Harmonic(6, 7, 8, harmonicFunctionType.Sin);
        const zeroHarmonic = new Harmonic(0, 0, 0, harmonicFunctionType.Sin);
        state.tmpHarmonic = newHarmonic;
        const action = actions.addHarmonic();
        const newState = chartDrawerReducer(state, action);
        expect(newState.harmonics.length - state.harmonics.length).toBe(1);
        expect(isHarmonicsEqual(newState.harmonics[newState.harmonics.length - 1], newHarmonic)).toBeTruthy();
        expect(isHarmonicsEqual(newState.tmpHarmonic, zeroHarmonic)).toBeTruthy();
    });
    it('can change "tmp" harmonic', () => {
        const state = getInitialState();
        const newHarmonic = new Harmonic(6, 7, 8, harmonicFunctionType.Sin);
        const action = actions.harmonicChange(newHarmonic, -1);
        const newState = chartDrawerReducer(state, action);
        expect(isHarmonicsEqual(newState.tmpHarmonic, newHarmonic)).toBeTruthy();
    });
    it('can change selected harmonic', () => {
        const state = getInitialState();
        const newHarmonic = new Harmonic(6, 7, 8, harmonicFunctionType.Sin);
        const action = actions.harmonicChange(newHarmonic, 0);
        const newState = chartDrawerReducer(state, action);
        expect(isHarmonicsEqual(newState.selectedHarmonic, newHarmonic)).toBeTruthy();
    });
    it('can\'t change non existing harmonic', () => {
        const state = getInitialState();
        const newHarmonic = new Harmonic(6, 7, 8, harmonicFunctionType.Sin);
        const action = actions.harmonicChange(newHarmonic, -2);
        expect( function(){chartDrawerReducer(state, action); } ).toThrow(RangeError);
    });
    it('can delete existing harmonic', () => {
        const state = getInitialState();
        const action = actions.deleteHarmonic(0);
        const newState = chartDrawerReducer(state, action);
        const harmonicsList = getHarmonicsList();
        expect(newState.harmonics.length - state.harmonics.length).toBe(-1);
        expect(isHarmonicsEqual(newState.harmonics[0], harmonicsList[1])).toBeTruthy();
        expect(isHarmonicsEqual(newState.harmonics[1], harmonicsList[2])).toBeTruthy();
    });
    it('can\'t delete non existing harmonic', () => {
        const state = getInitialState();
        const action = actions.deleteHarmonic(-1);
        expect( function(){chartDrawerReducer(state, action); } ).toThrow(RangeError);
    });
});