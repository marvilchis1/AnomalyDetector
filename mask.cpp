#include "mask.h"

Mask::Mask() {
    m_length = 0;
    m_apothem = 0;
}

Mask::Mask(MaskType mask_type, int mask_apothem) : Mask() {
    Set(mask_type, mask_apothem);
}

Mask::Mask(std::vector<double> mask_vector) {
    Set(mask_vector);
}

bool Mask::Set(MaskType mask_type, int mask_apothem ) {
    if (mask_type != MaskType::GAUSSIAN_BLUR && mask_apothem > 1) return false;
    if (mask_apothem < 1) return false;
    
    m_apothem = mask_apothem;
    m_length = 2*m_apothem + 1;
    
    if (!MaskSelector(mask_type)) return false;

    return true;

}

bool Mask::Set(std::vector<double> mask_vector) {
    if( mask_vector.size() < 9) return false;

    m_length = sqrt(mask_vector.size());
    m_apothem = (m_length - 1)/2;

    m_mask = mask_vector;

    return true;
}

bool Mask::MaskSelector(MaskType mask_type) {
    switch (mask_type) {
        case MaskType::FOCUS:
            m_mask = {
                        0.0, -1/9.0, 0.0,
                        -1/9, 5/9.0, -1/9.0,
                        0.0, -1/9.0, 0.0
                     };
            return true;

        case MaskType::BLUR:
            m_mask = {
                        1/9.0, 1/9.0, 1/9.0,
                        1/9.0, 1/9.0, 1/9.0,
                        1/9.0, 1/9.0, 1/9.0
                     };
            return true;

        case MaskType::EDGE_ENHANCEMENT:
            m_mask = {
                        0.0, 0.0, 0.0,
                        -1/9.0, 1/9.0, 0.0,
                        0.0, 0.0, 0.0
                     };
            return true;

        case MaskType::EMBOSSED:
            m_mask = {
                        -2/9.0, -1/9.0, 0.0,
                        -1/9.0, 1/9.0, 1/9.0,
                        0.0, 1/9.0, 2/9.0
                     };
            return true;

        case MaskType::EDGE_DETECTION:
            m_mask = {
                        0.0, 1/9.0, 0.0,
                        1/9.0, -4/9.0, 1/9.0,
                        0.0, 1/9.0, 0.0
                    };
            return true;

        case MaskType::GAUSSIAN_BLUR:
            m_mask = GaussianMask(m_apothem);
            return true;
        
        default: ;
    }
    return false;
}

double Mask::At(int x, int y) {
    return m_mask[m_length*y + x];
}

std::vector<double> Mask::GetVectorMask() {
    return m_mask;
}

int Mask::MaskLength() {
    return m_length;
}

int Mask::MaskApothem() {
    return m_apothem;
}

int Mask::MaskSize() {
    return m_mask.size();
}

