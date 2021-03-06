    if (runTime.writeTime())
    {
        volSymmTensorField sigma
        (
            IOobject
            (
                "sigma",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            epss*rho_s*sigmaD
        );

        if (thermalStress)
        {
            const volScalarField& T = Tptr();
            sigma = sigma - I*(epss*rho_s*threeKalpha*T);
        }

        volScalarField sigmaEq
        (
            IOobject
            (
                "sigmaEq",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            sqrt((3.0/2.0)*magSqr(dev(sigma)))
        );

        Info<< "Max sigmaEq = " << max(sigmaEq).value()
            << endl;

        runTime.write();
    }
