requires(qtHaveModule(widgets))
TEMPLATE      = subdirs

SUBDIRS             =   PDFAppForRPi \
                        qtpdf

PDFAppForRpi.depends = qtpdf