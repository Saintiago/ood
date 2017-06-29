import {ChartDrawerAction} from '../actions/ChartDrawerActions';
import {ChartDrawerState} from '../types/ChartDrawerState';
import * as event from '../constants/ChartDrawerEvents';
import Harmonic from '../components/Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

export function chartDrawerReducer(state: ChartDrawerState, action: ChartDrawerAction): ChartDrawerState {
    switch (action.type) {
        case event.SELECT_HARMONIC:
            if (action.index < 0 || action.index >= state.harmonics.length) {
                throw new RangeError();
            }
            return {...state, selectedHarmonic: state.harmonics[action.index], selectedHarmonicIndex: action.index};
        case event.TOGGLE_ADD_DIALOG:
            return {...state, addDialogVisible: !state.addDialogVisible};
        case event.SELECT_TAB:
            return {...state, tabSelected: action.newValue};
        case event.ADD_HARMONIC:
            let newTmpHarmonic = new Harmonic(0, 0, 0, harmonicFunctionType.Sin);
            return {
                ...state, harmonics: [
                    ...state.harmonics,
                    state.tmpHarmonic
                ],
                tmpHarmonic: newTmpHarmonic,
                addDialogVisible: false,
                selectedHarmonicIndex: state.harmonics.length,
                selectedHarmonic: newTmpHarmonic
            };
        case event.HARMONIC_CHANGE:
            if (action.index < -1 || action.index >= state.harmonics.length) {
                throw new RangeError();
            }
            if (action.index === -1) {
                return { ...state, tmpHarmonic: action.harmonic };
            } else {
                return { ...state, selectedHarmonic: action.harmonic};
            }

        case event.DELETE_HARMONIC:
            if (action.index < 0 || action.index >= state.harmonics.length) {
                throw new RangeError();
            }
            let harmonics = state.harmonics;
            delete harmonics[action.index];
            let newHarmonics = harmonics.filter(n => n);
            let newSelectedIndex = Math.max(0, state.selectedHarmonicIndex - 1);
            return {
                ...state,
                harmonics: newHarmonics,
                selectedHarmonicIndex: newSelectedIndex,
                selectedHarmonic: newHarmonics[newSelectedIndex]
            };
        default:
            return state;
    }
}