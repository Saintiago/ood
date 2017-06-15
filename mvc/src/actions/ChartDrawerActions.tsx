import * as constants from '../constants/ChartDrawerEvents';

export interface SelectHarmonic {
    type: constants.SELECT_HARMONIC;
    payload: number;
}

export function selectHarmonic(index: number): SelectHarmonic {
    return {
        type: constants.SELECT_HARMONIC,
        payload: index
    }
}

// TODO: refactor with redux-actions