add_executable(linkanalysis
    main.cc
    graph.cc graph.h
    linkanalysis.h
    pagerank.cc
    hits.cc
    simrank.cc
    )

target_link_libraries(linkanalysis fmt)