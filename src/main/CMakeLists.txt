INCLUDE_DIRECTORIES (
    ../utility
    ../Geometry
    ../models
    ../math
    ../AutoEquation
    ../GeomModels
    ../Equation
    ../tclapi
    ../errorSystem
    ../Circuit/data
    ../Data
    ../meshing
    ../MathEval
    ../common_api
    ../pythonapi
    ${TCL_INCLUDE}
    ${PYTHON_INCLUDE}
)

SET (LIBRARIES
    tclapi_interpreter
    commands
    Data
    AutoEquation
    meshing
    GeomModels
    Equation
    Geometry
    math
    MathEval
    models
    myThread
    circuitSources
    circuitIdeal
    circuitData
    errorSystem
    tclapi_api
    utility
)

SET (PYLIBRARIES
    commands
    pythonapi_interpreter
    commands
    pythonapi_interpreter
    Data
    AutoEquation
    meshing
    GeomModels
    Equation
    Geometry
    math
    MathEval
    models
    myThread
    circuitSources
    circuitIdeal
    circuitData
    errorSystem
    pythonapi_api
    utility
)

ADD_EXECUTABLE (devsim devsim.cc)
#TARGET_LINK_LIBRARIES(devsim ${LIBRARIES} ${TCL_ARCHIVE} ${ZLIB_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE} ${TCLSQLITE3_ARCHIVE})
TARGET_LINK_LIBRARIES(devsim ${LIBRARIES} ${TCL_ARCHIVE} ${ZLIB_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE} ${SQLITE3_ARCHIVE} ${PTHREAD_LIB} ${SYMDIFF_ARCHIVE})

ADD_EXECUTABLE (devsim_py devsim_py.cc)
TARGET_LINK_LIBRARIES(devsim_py ${PYLIBRARIES} ${PYTHON_ARCHIVE} ${ZLIB_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE} ${SQLITE3_ARCHIVE} ${TCL_STUB} ${SYMDIFF_ARCHIVE})

IF (WIN32)
SET_TARGET_PROPERTIES(devsim PROPERTIES
        LINK_FLAGS " /NODEFAULTLIB:LIBMSVCRT"
	)
ENDIF (WIN32)
#TARGET_LINK_LIBRARIES(devsim ${LIBRARIES} ${TCL_ARCHIVE} ${ZLIB_ARCHIVE} ${PETSC_ARCHIVE} ${MPI_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE})


