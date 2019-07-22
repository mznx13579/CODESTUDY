//
//  BountyInfo.swift
//  BountyList
//
//  Created by 정성윤 on 23/07/2019.
//  Copyright © 2019 정성윤. All rights reserved.
//

import UIKit

class BountyInfo {
    var name: String
    var bounty: Int
    var image: UIImage? {
        return UIImage(named: "\(name).jpg")
    }
    
    init(name: String, bounty: Int) {
        self.name = name
        self.bounty = bounty
    }
}
