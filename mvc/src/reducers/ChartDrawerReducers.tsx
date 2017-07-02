import {ChartDrawerAction} from '../actions/ChartDrawerActions';
import {ChartDrawerState} from '../types/ChartDrawerState';
import * as event from '../constants/ChartDrawerEvents';
import Harmonic from '../components/Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import History from '../lib/history';

let harmonicsList = [] as Harmonic[];

harmonicsList.push(new Harmonic(4.5, 23, -1, harmonicFunctionType.Sin));
harmonicsList.push(new Harmonic(-11, 4, 1, harmonicFunctionType.Cos));
harmonicsList.push(new Harmonic(1, 1, 3, harmonicFunctionType.Sin));

let history = new History({
    harmonics: harmonicsList,
    selectedHarmonic: harmonicsList[0],
    tmpHarmonic: new Harmonic(0, 0, 0, harmonicFunctionType.Sin),
    selectedHarmonicIndex: 0,
    addDialogVisible: false,
    tabSelected: 'line'
});

export function chartDrawerReducer(state: ChartDrawerState, action: ChartDrawerAction): ChartDrawerState {

    let newState = {...state};

    switch (action.type) {
        case event.SELECT_HARMONIC:
            if (action.index < 0 || action.index >= newState.harmonics.length) {
                throw new RangeError();
            }
            newState.selectedHarmonic = newState.harmonics[action.index];
            newState.selectedHarmonicIndex = action.index;
            history.addNewSnapshot({...newState});
            break;
        case event.TOGGLE_ADD_DIALOG:
            newState.addDialogVisible = !newState.addDialogVisible;
            break;
        case event.UNDO:
            history.undo();
            return history.getLastState();
        case event.REDO:
            history.redo();
            return history.getLastState();
        case event.SELECT_TAB:
            newState.tabSelected = action.newValue;
            break;
        case event.ADD_HARMONIC:
            let newTmpHarmonic = new Harmonic(0, 0, 0, harmonicFunctionType.Sin);
            newState.harmonics = [
                ...newState.harmonics,
                newState.tmpHarmonic
            ];
            newState.selectedHarmonicIndex = Math.max(0, newState.harmonics.length - 1);
            newState.selectedHarmonic = newState.tmpHarmonic;
            newState.tmpHarmonic = newTmpHarmonic;
            newState.addDialogVisible = false;
            history.addNewSnapshot({...newState});
            break;
        case event.HARMONIC_CHANGE:
            if (action.index < -1 || action.index >= newState.harmonics.length) {
                throw new RangeError();
            }
            if (action.index === -1) {
                newState.tmpHarmonic = action.harmonic;
            } else {
                newState.selectedHarmonic = action.harmonic;
            }
            break;
        case event.DELETE_HARMONIC:
            if (action.index < 0 || action.index >= newState.harmonics.length) {
                throw new RangeError();
            }
            let harmonics = [...newState.harmonics];
            delete harmonics[action.index];
            let newHarmonics = harmonics.filter(n => n);
            let newSelectedIndex = Math.max(0, newState.selectedHarmonicIndex - 1);
            newState.harmonics = newHarmonics;
            newState.selectedHarmonicIndex = newSelectedIndex;
            newState.selectedHarmonic = newHarmonics[newSelectedIndex];
            history.addNewSnapshot({...newState});
            break;
        default:
            break;
    }

    return newState;
}