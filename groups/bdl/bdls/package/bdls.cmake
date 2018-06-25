include(bde_interface_target)
include(bde_package)
include(bde_struct)

bde_prefixed_override(bdls process_package)
function(bdls_process_package retPackage)
    process_package_base("" package ${ARGN})

    bde_struct_get_field(interfaceTarget ${package} INTERFACE_TARGET)
    bde_interface_target_link_libraries(
        ${interfaceTarget}
        PUBLIC
            $<$<CXX_COMPILER_ID:SunPro>:socket>
    )

    bde_return(${package})
endfunction()