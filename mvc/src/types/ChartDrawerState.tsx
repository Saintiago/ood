import Harmonic from '../components/Harmonic';

export interface ChartDrawerState {
    harmonics: Harmonic[];
    tmpHarmonic: Harmonic;
    selectedHarmonic: number;
    addDialogVisible: boolean;
    tabSelected: string;
}