if(USE_OPENVINO AND NOT EXISTS "${ORT_LIB_DIR}/${ONNXRUNTIME_PROVIDERS_OPENVINO_LIB}")
  message(FATAL_ERROR "Expected the ONNX Runtime providers OpenVINO library to be found at ${ORT_LIB_DIR}/${ONNXRUNTIME_PROVIDERS_OPENVINO_LIB}. Actual: Not found.")
endif()

if(USE_OPENVINO)
  add_compile_definitions(USE_OPENVINO=1)
else()
  add_compile_definitions(USE_OPENVINO=0)
endif()