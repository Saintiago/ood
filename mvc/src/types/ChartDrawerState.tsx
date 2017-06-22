import Harmonic from '../components/Harmonic';

export interface ChartDrawerState {
    harmonics: Harmonic[];
    selectedHarmonic: Harmonic;
    tmpHarmonic: Harmonic;
    selectedHarmonicIndex: number;
    addDialogVisible: boolean;
    tabSelected: string;
}