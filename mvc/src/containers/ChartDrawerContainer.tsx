import ChartDrawer from '../components/ChartDrawer';
import * as actions from '../actions/ChartDrawerActions';
import { ChartDrawerState } from '../types/ChartDrawerState';
import { connect, Dispatch } from 'react-redux';
import Harmonic from '../components/Harmonic';

export function mapStateToProps({ harmonics, tmpHarmonic, selectedHarmonic, addDialogVisible }: ChartDrawerState) {
    return {
        harmonics,
        tmpHarmonic,
        selected: selectedHarmonic,
        addDialogVisible
    };
}

export function mapDispatchToProps(dispatch: Dispatch<actions.SelectHarmonic>) {
    return {
        onSelectHarmonic: (index: number) => dispatch(actions.selectHarmonic(index)),
        onAddDialogClicked: () => dispatch(actions.toggleAddDialog()),
        onAddClicked: () => dispatch(actions.addHarmonic()),
        onCancelClicked: () => dispatch(actions.toggleAddDialog()),
        onAddHarmonicChange: (newHarmonic: Harmonic) => dispatch(actions.addHarmonicChange(newHarmonic)),
        onDeleteClicked: (index: number) => dispatch(actions.deleteHarmonic(index))
    };
}

export default connect(mapStateToProps, mapDispatchToProps)(ChartDrawer);