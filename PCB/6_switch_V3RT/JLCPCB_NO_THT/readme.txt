Eagle Schematic: DNVT_box3rt.sch
Eagle Layout: DNVT_box3rt.brd
Schematic PDF: DNVT_box3rt.pdf

JLCPCB Gerbers: DNVT_box3rt_2023-02-21.zip
JLCPCB Top Placement: DNVT_box3rt_top_cpl.csv
JLCPCB BOM: DNVT_box3rt_top_bom.csv

Through Hole BOM: DNVT_box3rt_th_bom.csv
Additional BOM: DNVT_box3r_aux_bom.csv

Notes:

-With this set of files, JLCPCB will only assemble the surface mount parts. This was used to order initial runs of the DNVT switch prior to when I figured out how to get them to assemble through holes parts (their scripts do not handle through hole parts, so you have to manually add them to the BOM and placement file).
-The rotation of the inductors and RS422 transceivers must be manually corrected at the placement review step after uploading to JLCPCB.
-The JLCPCB BOM maps all surface mount parts to parts available in JLCPCB's parts library.
-The bottom side parts are optional (additional chassis ground to Pico Ground capacitors and uSD card holder)
-The Digikey BOM lists through hole parts which must be manually assembled as well as the LCSC alternatives for these parts where available.
-The additional BOM lists parts not captured in the Eagle BOM export: headers for the Pico, the case, OLED screen, Front and back plates, screws, nuts, cable for screen, and 48V power supply.

Designer Contact: Robert Ruark: rob@robruark.com