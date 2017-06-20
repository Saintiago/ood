import ChartDrawer from '../components/ChartDrawer';
import * as actions from '../actions/ChartDrawerActions';
import { ChartDrawerState } from '../types/ChartDrawerState';
import { connect, Dispatch } from 'react-redux';
import Harmonic from '../components/Harmonic';

export function mapStateToProps({
                                    harmonics,
                                    tmpHarmonic,
                                    selectedHarmonic,
                                    addDialogVisible,
                                    tabSelected
}: ChartDrawerState) {
    return {
        harmonics,
        tmpHarmonic,
        selected: selectedHarmonic,
        addDialogVisible,
        tabSelected
    };
}

export function mapDispatchToProps(dispatch: Dispatch<actions.SelectHarmonic>) {
    return {
        onSelectHarmonic: (index: number) => dispatch(actions.selectHarmonic(index)),
        onAddDialogClicked: () => dispatch(actions.toggleAddDialog()),
        onAddClicked: () => dispatch(actions.addHarmonic()),
        onCancelClicked: () => dispatch(actions.toggleAddDialog()),
        onHarmonicChange: (harmonic: Harmonic, index: number) => dispatch(actions.harmonicChange(harmonic, index)),
        onDeleteClicked: (index: number) => dispatch(actions.deleteHarmonic(index)),
        onTabSelected: (newValue: string) => dispatch(actions.selectTab(newValue))
    };
}

export default connect(mapStateToProps, mapDispatchToProps)(ChartDrawer);