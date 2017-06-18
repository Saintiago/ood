import {ChartDrawerAction} from '../actions/ChartDrawerActions';
import {ChartDrawerState} from '../types/ChartDrawerState';
import * as event from '../constants/ChartDrawerEvents';
import Harmonic from '../components/Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

export function selectHarmonic(state: ChartDrawerState, action: ChartDrawerAction): ChartDrawerState {
    switch (action.type) {
        case event.SELECT_HARMONIC:
            return {...state, selectedHarmonic: action.index};
        case event.TOGGLE_ADD_DIALOG:
            return {...state, addDialogVisible: !state.addDialogVisible};
        case event.ADD_HARMONIC:
            return {
                ...state, harmonics: [
                    ...state.harmonics,
                    state.tmpHarmonic
                ],
                tmpHarmonic: new Harmonic(0, 0, 0, harmonicFunctionType.Sin),
                addDialogVisible: false
            };
        case event.ADD_HARMONIC_CHANGE:
            return { ...state, tmpHarmonic: action.harmonic };
        default:
            return state;
    }
}

/*
 todos: [
 ...state.todos,
 {
 text: action.text,
 completed: false
 }
 ]
 */