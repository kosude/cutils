set(TEMPLATES_DIR "${CMAKE_CURRENT_LIST_DIR}/templates")

set(WARNING_COMMENT "<!-- This file has been automatically generated! Edits will be overwritten on the next build! -->")

file(READ "${TEMPLATES_DIR}/template_head.html" TEMPLATE_head)
file(READ "${TEMPLATES_DIR}/template_header.html" TEMPLATE_header)
file(READ "${TEMPLATES_DIR}/template_footer.html" TEMPLATE_footer)

file(COPY "${CMAKE_CURRENT_LIST_DIR}/style" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

configure_file("${CMAKE_CURRENT_LIST_DIR}/index.html" "${CMAKE_CURRENT_BINARY_DIR}/index.html" @ONLY)
configure_file("${CMAKE_CURRENT_LIST_DIR}/clist.html" "${CMAKE_CURRENT_BINARY_DIR}/clist.html" @ONLY)
