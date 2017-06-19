import * as constants from '../constants/ChartDrawerEvents';
import Harmonic from '../components/Harmonic';

export interface SelectHarmonic {
    type: constants.SELECT_HARMONIC;
    index: number;
}

export interface AddHarmonic {
    type: constants.ADD_HARMONIC;
}

export interface DeleteHarmonic {
    type: constants.DELETE_HARMONIC;
    index: number;
}

export interface ToggleAddDialog {
    type: constants.TOGGLE_ADD_DIALOG;
}

export interface SelectTab {
    type: constants.SELECT_TAB;
    newValue: string
}

export interface AddHarmonicChange {
    type: constants.ADD_HARMONIC_CHANGE;
    harmonic: Harmonic;
}

export type ChartDrawerAction =
    SelectHarmonic
    | ToggleAddDialog
    | AddHarmonic
    | AddHarmonicChange
    | DeleteHarmonic
    | SelectTab;

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

export function deleteHarmonic(index: number): DeleteHarmonic {
    return {
        type: constants.DELETE_HARMONIC,
        index
    };
}

export function toggleAddDialog(): ToggleAddDialog {
    return {
        type: constants.TOGGLE_ADD_DIALOG
    };
}

export function selectTab(newValue: string): SelectTab {
    return {
        type: constants.SELECT_TAB,
        newValue
    };
}

export function addHarmonicChange(harmonic: Harmonic): AddHarmonicChange {
    return {
        type: constants.ADD_HARMONIC_CHANGE,
        harmonic
    };
}

// TODO: refactor with redux-actions