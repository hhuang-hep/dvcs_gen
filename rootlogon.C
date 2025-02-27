{
    cout<<"rootlogon.C in the Hao's directory has been loaded"<<endl;
    
    char *inc_nps_soft = gSystem->ExpandPathName("/group/nps/hhuang/software/NPS_SOFT");
    gInterpreter->AddIncludePath(inc_nps_soft);
    delete [] inc_nps_soft;

    char *inc_dvcs_soft = gSystem->ExpandPathName("/group/nps/hhuang/software/dvcs_gen");
    gInterpreter->AddIncludePath(inc_dvcs_soft);
    delete [] inc_dvcs_soft;
}
