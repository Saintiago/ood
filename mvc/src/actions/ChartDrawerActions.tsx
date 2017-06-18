import * as constants from '../constants/ChartDrawerEvents';
import Harmonic from '../components/Harmonic';

export interface SelectHarmonic {
    type: constants.SELECT_HARMONIC;
    index: number;
}

export interface AddHarmonic {
    type: constants.ADD_HARMONIC;
}

export interface ToggleAddDialog {
    type: constants.TOGGLE_ADD_DIALOG;
}

export interface AddHarmonicChange {
    type: constants.ADD_HARMONIC_CHANGE;
    harmonic: Harmonic;
}

export type ChartDrawerAction = SelectHarmonic | ToggleAddDialog | AddHarmonic | AddHarmonicChange;

export function selectHarmonic(index: number): SelectHarmonic {
    return {
        type: constants.SELECT_HARMONIC,
        index
    };
}

export function addHarmonic(): AddHarmonic {
    return {
        type: constants.ADD_HARMONIC
    };
}

export function toggleAddDialog(): ToggleAddDialog {
    return {
        type: constants.TOGGLE_ADD_DIALOG
    };
}

export function addHarmonicChange(harmonic: Harmonic): AddHarmonicChange {
    return {
        type: constants.ADD_HARMONIC_CHANGE,
        harmonic
    };
}

// TODO: refactor with redux-actions