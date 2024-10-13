///|/ Copyright (c) Prusa Research 2023 Enrico Turri @enricoturri1966, Pavel Mikuš @Godrak
///|/
///|/ libvgcode is released under the terms of the AGPLv3 or higher
///|/
#ifndef VGCODE_PATHVERTEX_HPP
#define VGCODE_PATHVERTEX_HPP

#include "Types.hpp"

#include <cfloat>

namespace libvgcode {

//
// Struct representating a gcode move (toolpath segment)
//
struct PathVertex
{
    //
    // Segment end position
    //
    Vec3 position{ FLT_MAX, FLT_MAX, FLT_MAX };
    //
    // Segment height
    //
    float height{ 0.0f };
    //
    // Segment width
    //
    float width{ 0.0f };
    //
    // Segment speed
    //
    float feedrate{ 0.0f };
    //
    // Segment actual speed
    //
    float actual_feedrate{ 0.0f };
    //
    // Segment mm3_per_mm
    //
    float mm3_per_mm{ 0.0f };
    //
    // Segment fan speed
    //
    float fan_speed{ 0.0f };
    //
    // Segment temperature
    //
    float temperature{ 0.0f };
#if VGCODE_ENABLE_COG_AND_TOOL_MARKERS
    //
    // Segment weight
    //
    float weight{ 0.0f };
#endif // VGCODE_ENABLE_COG_AND_TOOL_MARKERS
    //
    // Segment extrusion role
    //
    EGCodeExtrusionRole role{ EGCodeExtrusionRole::None };
    //
    // Segment move type
    //
    EMoveType type{ EMoveType::Noop };
    //
    // Segment gcode line id
    //
    uint32_t gcode_id{ 0 };
    //
    // Segment layer id
    //
    uint32_t layer_id{ 0 };
    //
    // Segment extruder id
    //
    uint8_t extruder_id{ 0 };
    //
    // Segment color id
    //
    uint8_t color_id{ 0 };
    //
    // Segment estimated times
    //
    std::array<float, TIME_MODES_COUNT> times{ 0.0f, 0.0f };

    //
    // Return true if the segment is an extrusion move
    //
    bool is_extrusion() const;
    //
    // Return true if the segment is an travel move
    //
    bool is_travel() const;
    //
    // Return true if the segment is an option
    // See: EOptionType
    //
    bool is_option() const;
    //
    // Return true if the segment is a wipe move
    //
    bool is_wipe() const;
    //
    // Return true if the segment was generated by custom gcode
    //
    bool is_custom_gcode() const;
    //
    // Return the volumetric flow rate of the segment
    //
    float volumetric_rate() const { return feedrate * mm3_per_mm; }
    //
    // Return the acutal volumetric flow rate of the segment
    //
    float actual_volumetric_rate() const { return actual_feedrate * mm3_per_mm; }

    static const PathVertex DUMMY_PATH_VERTEX;
};

} // namespace libvgcode

#endif // VGCODE_PATHVERTEX_HPP