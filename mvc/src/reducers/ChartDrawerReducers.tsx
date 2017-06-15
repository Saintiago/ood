// src/reducers/index.tsx

import { SelectHarmonic } from '../actions/ChartDrawerActions';
import { ChartDrawerState } from '../types/ChartDrawerState';
import { SELECT_HARMONIC } from '../constants/ChartDrawerEvents';

export function selectHarmonic(state: ChartDrawerState, action: SelectHarmonic): ChartDrawerState {
    switch (action.type) {
        case SELECT_HARMONIC:
            return { ...state, selectedHarmonic: action.payload };
    }
    return state;
}