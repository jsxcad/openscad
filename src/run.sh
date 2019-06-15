g++ \
     -I./ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/eigen3 -I./ext/libtess2/Include \
     -DSTACKSIZE=8388608 -DOPENSCAD_VERSION=2019.06.14 -DOPENSCAD_SHORTVERSION=2019.06.14 -DOPENSCAD_YEAR=2019.0 -DOPENSCAD_MONTH=06.0 -DOPENSCAD_DAY=14.0 \
     -lboost_filesystem -lboost_system -lboost_regex -lglib-2.0 -ldouble-conversion \
     mini.cc Tree.cc builtincontext.cc value.cc context.cc AST.cc handle_dep.cc printutils.cc ../objects/parser.cxx comment.cpp parameter/parameterset.cpp FileModule.cc node.cc \
     ModuleInstantiation.cc localscope.cc Assignment.cc NodeVisitor.cc nodedumper.cc builtin.cc boost-utils.cc evalcontext.cc ../objects/lexer.cxx function.cc expr.cc module.cc \
     UserModule.cc annotation.cc ../objects/comment_parser.cxx modcontext.cc StatCache.cc ModuleCache.cc parsersettings.cc feature.cc progress.cc PlatformUtils-posix.cc \
     ../objects/comment_lexer.cxx PlatformUtils.cc version.cc func.cc linalg.cc degree_trig.cc GroupModule.cc dxfdim.cc fileutils.cc dxfdata.cc calc.cc Polygon2d.cc \
     transform.cc color.cc projection.cc polyset.cc polyset-utils.cc GeometryUtils.cc csgops.cc control.cc offset.cc primitives.cc linearextrude.cc rotateextrude.cc \
     render.cc cgaladv.cc

#     ext/libtess2/Source/bucketalloc.c ext/libtess2/Source/dict.c ext/libtess2/Source/geom.c ext/libtess2/Source/mesh.c ext/libtess2/Source/priorityq.c \
#     ext/libtess2/Source/sweep.c ext/libtess2/Source/tess.c

#     surface.cc import.cc 
