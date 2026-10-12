qt_add_library(vrpmapeditor_core STATIC
    ccentralwidget.cpp ccentralwidget.h ccentralwidget.ui
    GenerateRoutesUi.cpp GenerateRoutesUi.h GenerateRoutesUi.ui CustomRoutesUi.ui
    GLWidget.cpp GLWidget.h
    NodeViewDialog.cpp NodeViewDialog.h nodeviewdialog.ui
    UiModels.cpp UiModels.h
    VehicleCostsWidget.cpp VehicleCostsWidget.h VehicleCostsWidget.ui
    vrpmapeditorqt.cpp vrpmapeditorqt.h vrpmapeditorqt.ui FindNodeUi.ui
    Classes/AppBaseState.cpp Classes/AppBaseState.h
    Classes/AppMapEdit/AppMapEdit.cpp Classes/AppMapEdit/AppMapEdit.h
    Classes/AppMapEdit/GraphAlgorithms/GraphAlgorithm.cpp
    Classes/AppMapEdit/GraphAlgorithms/GraphAlgorithm.h
    Classes/AppMapEdit/GraphMap/GraphMap.cpp Classes/AppMapEdit/GraphMap/GraphMap.h
    Classes/AppMapEdit/GraphMap/GraphNode.cpp Classes/AppMapEdit/GraphMap/GraphNode.h
    Classes/AppMapEdit/GraphMap/GraphRoute.cpp Classes/AppMapEdit/GraphMap/GraphRoute.h
    Classes/AppMapEdit/InputMapEdit.cpp Classes/AppMapEdit/InputMapEdit.h
    Classes/AppMapEdit/MapOperations.cpp Classes/AppMapEdit/MapOperations.h
    Classes/AppMapEdit/MapOperationsGraphics.cpp Classes/AppMapEdit/MapOperationsGraphics.h
    Classes/AppMapEdit/MapOperationsIAccess.cpp Classes/AppMapEdit/MapOperationsIAccess.h
    Classes/AppMapEdit/MapOperationsInput.cpp Classes/AppMapEdit/MapOperationsInput.h
    Classes/AppMapEdit/OMapEvent.cpp Classes/AppMapEdit/OMapEvent.h
    Classes/AppMapEdit/RoutesGenerator/ORoutesGenerator.cpp
    Classes/AppMapEdit/RoutesGenerator/ORoutesGenerator.h
    Classes/AppMapEdit/RoutesGenerator/OVehicleRoute.cpp
    Classes/AppMapEdit/RoutesGenerator/OVehicleRoute.h
    Classes/Draw2D.cpp Classes/Draw2D.h
    Classes/GLCamera.cpp Classes/GLCamera.h
    Classes/InputBaseState.cpp Classes/InputBaseState.h
    Classes/InputMgr.cpp Classes/InputMgr.h
    Classes/Math/Matrix4x4.cpp Classes/Math/Matrix4x4.h
    Classes/Math/Quaternion.cpp Classes/Math/Quaternion.h
    Classes/Math/Vector3.cpp Classes/Math/Vector3.h
    Classes/Math/Vector4.cpp Classes/Math/Vector4.h
    Classes/Utils/math_utils.cpp Classes/Utils/math_utils.h
    Classes/Utils/OTextures.cpp Classes/Utils/OTextures.h
    Classes/Utils/WorkerThread.h
    Classes/VariousObjects.cpp Classes/VariousObjects.h
    Classes/xml/XmlDoc.cpp Classes/xml/XmlDoc.h
)

target_compile_features(vrpmapeditor_core PUBLIC cxx_std_17)
set_target_properties(vrpmapeditor_core PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(vrpmapeditor_core PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Classes"
    "${CMAKE_CURRENT_BINARY_DIR}/vrpmapeditor_core_autogen/include"
    "${CMAKE_CURRENT_BINARY_DIR}/vrpmapeditor_core_autogen/include_$<CONFIG>"
)
target_link_libraries(vrpmapeditor_core PUBLIC
    Qt6::Widgets Qt6::Network Qt6::OpenGLWidgets OpenGL::GL
)
if(MSVC)
    target_compile_options(vrpmapeditor_core PRIVATE /utf-8)
    target_compile_definitions(vrpmapeditor_core PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

qt_add_executable(VRPMapEditorQt main.cpp vrpmapeditorqt.qrc)
target_link_libraries(VRPMapEditorQt PRIVATE vrpmapeditor_core)
if(WIN32)
    target_sources(VRPMapEditorQt PRIVATE VRPMapEditorQt.rc)
endif()
set_target_properties(VRPMapEditorQt PROPERTIES WIN32_EXECUTABLE TRUE)

install(TARGETS VRPMapEditorQt RUNTIME DESTINATION bin)
qt_generate_deploy_app_script(
    TARGET VRPMapEditorQt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT "${deploy_script}")

if(BUILD_TESTING)
    find_package(Qt6 6.10.1 REQUIRED COMPONENTS Test)
    qt_add_executable(migration_tests tests/migration_tests.cpp vrpmapeditorqt.qrc)
    target_link_libraries(migration_tests PRIVATE vrpmapeditor_core Qt6::Test)
    target_compile_definitions(migration_tests PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
    add_test(NAME migration COMMAND migration_tests -platform offscreen
        legacyMapRoundTrip routeWireFormat unicodeNodeRoundTrip portableMath
        networkResponses malformedDirections workerShutdown)
    option(VRPMAPEDITOR_TEST_OPENGL "Run the OpenGL smoke test (requires a desktop display)" OFF)
    if(VRPMAPEDITOR_TEST_OPENGL)
        add_test(NAME opengl_smoke COMMAND migration_tests openGLSmoke)
    endif()
endif()
