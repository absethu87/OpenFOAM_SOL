    Info << "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info << "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
  
   // volScalarField rho
   // (
     //   IOobject
     //   (
     //       "rho",
    //        runTime.timeName(),
     //       mesh,
     //       IOobject::READ_IF_PRESENT,
     //       IOobject::AUTO_WRITE
     //   ),
     //   <initial_scalar_value_of_rho>
    //);
    
    Info<< "Reading transportProperties\n" << endl;
    IOdictionary transportProperties
    (
	IOobject
	(
		"transportProperties",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	) 
     );
  
	dimensionedScalar rho
	(
	transportProperties.lookup("rho")
	);

    //Info<< "Reading controlDict\n" << endl;
    //IOdictionary controlDict
    //(
	//IOobject
	//(
	//	"controlDict",
	//	runTime.constant(),
	//	mesh,
	//	IOobject::MUST_READ,
	//	IOobject::NO_WRITE
	//) 
     //);
  
	//const double sourceWriteTime
	//(
	//controlDict.lookup("sourceWriteTime")
	//);
    
    Info<< "Reading field acoSor\n" << endl;
    volScalarField acoSor
    (
	IOobject
	(
	    "acoSor",
	     runTime.timeName(),
	     mesh,
	    IOobject::MUST_READ,
	    IOobject::AUTO_WRITE
        ),
       mesh
    );

#   include "createPhi.H"


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("PISO"), pRefCell, pRefValue);


    singlePhaseTransportModel laminarTransport(U, phi);

    //autoPtr<incompressible::RASModel> turbulence
	autoPtr<incompressible::turbulenceModel> turbulence
    (
        //incompressible::RASModel::New(U, phi, laminarTransport)
		incompressible::turbulenceModel::New(U, phi, laminarTransport)
    );
