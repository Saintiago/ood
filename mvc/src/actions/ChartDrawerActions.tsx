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
    newValue: string;
}

export interface HarmonicChange {
    type: constants.HARMONIC_CHANGE;
    harmonic: Harmonic;
    index: number;
}

export type ChartDrawerAction =
    SelectHarmonic
    | ToggleAddDialog
    | AddHarmonic
    | DeleteHarmonic
    | SelectTab
    | HarmonicChange;

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

export function harmonicChange(harmonic: Harmonic, index: number): HarmonicChange {
    return {
        type: constants.HARMONIC_CHANGE,
        harmonic,
        index
    };
}

// TODO: refactor with redux-actions